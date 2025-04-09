SELECT name
FROM people JOIN stars ON people.id = stars.person_id
WHERE stars.movie_id IN (SELECT movies.id
FROM movies JOIN stars ON movies.id = stars.movie_id JOIN people ON people.id = stars.person_id
WHERE people.name = 'Kevin Bacon')
AND stars.person_id != (SELECT person_id FROM stars JOIN people ON people.id = stars.person_id WHERE people.name = 'Kevin Bacon');
