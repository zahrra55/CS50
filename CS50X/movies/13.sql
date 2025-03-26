SELECT DISTINCT people.name
FROM stars as others

JOIN movies ON others.movie_id = movies.id
JOIN stars as kevin ON kevin.movie_id = movies.id
JOIN people ON people.id = others.person_id
JOIN people as kevin_person ON kevin_person.id = kevin.person_id

WHERE kevin_person.name = "Kevin Bacon"
AND kevin_person.birth = 1958
AND people.name != "Kevin Bacon";
