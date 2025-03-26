SELECT DISTINCT people.name
FROM movies
JOIN directors ON movies.id = directors.movie_id
JOIN people ON people.id = directors.person_id
JOIN ratings ON ratings.movie_id = directors.movie_id
WHERE ratings.rating >= 9.0;

