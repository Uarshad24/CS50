
SELECT title
FROM movies JOIN ratings ON movies.id = ratings.movie_id JOIN stars ON stars.movie_id = movies.id JOIN people ON stars.person_id = people.id
WHERE people.name = 'Chadwick Boseman'
ORDER BY rating DESC
LIMIT 5;
