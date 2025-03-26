SELECT movies.title
FROM movies
JOIN stars as BC ON BC.movie_id = movies.id
JOIN people as PBC ON PBC.id = BC.person_id
JOIN stars as JL ON JL.movie_id = movies.id
JOIN people as PJL ON PJL.id = JL.person_id
WHERE PJL.name = "Jennifer Lawrence"
AND PBC.name = "Bradley Cooper";
