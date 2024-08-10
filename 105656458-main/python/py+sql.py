import csv

from cs50 import SQL

db = SQL("sqlite:///sample.db")

favorite = input("Favorite: ")

rows = db.execute("SELECT COUNT(*) AS n FROM sample WHERE LOWER(language) LIKE LOWER(?)", favorite)

# rows is an array of dicts where there is only 1 column

row = rows[0]

print(row["n"])
