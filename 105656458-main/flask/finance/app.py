import os
import datetime
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
    cash = round(cash)
    stocks = db.execute("SELECT symbol, SUM(shares) AS total_shares FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
    grandtotal = cash

    for stock in stocks:
        stock["price"] = lookup(stock["symbol"])["price"]
        grandtotal += int(stock["price"]) * stock["total_shares"]

    grandtotal = round(grandtotal)

    return render_template("index.html", cash=cash, grandtotal=grandtotal, stocks=stocks)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol") or not request.form.get("shares"):
            return apology("Fill in the fields")

        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("Invalid number of shares", 403)

        quote = lookup(request.form.get("symbol"))
        price = quote["price"]
        symbol = quote["symbol"]
        total = price * shares
        user_id = session["user_id"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
        updated_cash = cash - total
        date = datetime.datetime.now()

        if quote == None:
            return apology("Stock does not exist")

        if shares <= 0:
            return apology("Invalid number of shares")

        if cash < total:
            return apology("You do not have enough money")

        db.execute("UPDATE users SET cash = ? WHERE id = ?", updated_cash, user_id)
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date)VALUES (?,?,?,?,?)", user_id, symbol, shares, total, date)

        flash("Bought!")

        return redirect("/")

    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    stocks = db.execute("SELECT symbol, price, shares, date FROM transactions WHERE user_id = ?", user_id)
    return render_template("history.html", stocks=stocks, abs=abs)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        #  user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        stocks = lookup(request.form.get("symbol"))
        if stocks == None:
            return apology("stock does not exist", 403)
        else:
            return render_template("quoted.html", stocks=stocks)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        if request.form.get("password") != request.form.get("confirmation"):
            return apology("confirmation password does not match", 403)

        name = request.form.get("username")
        password = generate_password_hash(request.form.get("password"))

        try:
            db.execute("INSERT INTO users (username, hash) VALUES(?,?)", name, password)
        except ValueError:
            return apology("the username already exists", 403)
        return render_template("login.html")

    else:
        return render_template("register.html")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        user_id = session["user_id"]
        symbols = db.execute("SELECT DISTINCT symbol FROM transactions WHERE user_id = ?", user_id)
        return render_template("sell.html", symbols=symbols)
    else:
        # Retrieve and validate form data
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        print(symbol)

        if not symbol or not shares:
            return apology("missing symbol or shares", 403)

        try:
            quantity = int(shares)
        except ValueError:
            return apology("invalid shares", 403)

        if quantity <= 0:
            return apology("shares must be positive", 403)

        quote = lookup(symbol)
        if quote is None:
            return apology("symbol not found", 403)

        # Retrieve user's shares for the symbol
        user_id = session["user_id"]
        user_shares_row = db.execute("SELECT SUM(shares) as total_shares FROM transactions WHERE user_id = ? AND symbol = ?", user_id, symbol)
        if not user_shares_row or user_shares_row[0]["total_shares"] is None or user_shares_row[0]["total_shares"] < quantity:
            return apology("not enough shares", 403)

        # Retrieve user's cash
        cash_row = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        if not cash_row:
            return apology("user not found", 403)
        cash = cash_row[0]["cash"]

        total_price = quantity * quote["price"]
        updated_cash = cash + total_price  # Selling shares increases cash

        # Update user's cash in the database
        db.execute("UPDATE users SET cash = ? WHERE id = ?", updated_cash, user_id)
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)", user_id, symbol, -quantity, quote["price"])

        return redirect("/")

@app.route("/deposit", methods=["GET", "POST"])
@login_required
def deposit():
    if request.method == "GET":
        return render_template("deposit.html")
    else:
        if not request.form.get("sum"):
            return apology("incorrect money input", 403)

        try:
            sum = int(request.form.get("sum"))
        except ValueError:
            return apology("incorrect money input", 403)

        if sum <= 0:
            return apology("incorrect money input", 403)

        user_id = session["user_id"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
        updated_cash = cash + sum

        db.execute("UPDATE users SET cash = ? WHERE id = ?", updated_cash, user_id)
        return redirect("/")




