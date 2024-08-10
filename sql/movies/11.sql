SELECT title FROM movies, ratings, people, stars
 WHERE movies.id = stars.movie_id AND movies.id = ratings.movie_id AND people.id = stars.person_id
  AND name = 'Chadwick Boseman'
   ORDER BY rating DESC
    LIMIT 5;
