-- Keep a log of any SQL queries you execute as you solve the mystery.
1)
SELECT *
FROM crime_scene_reports
WHERE year = 2023 AND month = 7 AND day = 28 AND street = 'Humphrey Street' --To get the description of the crime report
2)
SELECT *
FROM interviews
WHERE transcript LIKE '%bakery%' -- To get the transcript of the witnesses
3)
SELECT name, city, (SELECT name FROM people WHERE phone_number = receiver) AS accomplice -- To find the receiver name
FROM atm_transactions JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number -- To get the person_id from the band_accounts
JOIN people ON people.id = bank_accounts.person_id -- using person_id to find the name of people who made atm_transactions on theft day
JOIN phone_calls ON phone_calls.caller = people.phone_number -- To Eliminate the people who did not make call on the given time
JOIN passengers ON passengers.passport_number = people.passport_number -- To get the passport_number
JOIN flights ON passengers.flight_id = flights.id -- To find out who took the flight on the next day of theft day
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate -- To find out who left the bakery parking within 10 mins after the theft
JOIN airports ON flights.destination_airport_id = airports.id -- To find the destination city of the theif
-- Conditions based on the witnesses interviews
WHERE atm_transactions.year = 2023 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND transaction_type = 'withdraw' AND atm_location = 'Leggett Street'
AND phone_calls.year = 2023 AND phone_calls.month = 7 AND phone_calls.day = 28 AND duration < 60
AND flights.year = 2023 AND flights.month = 7 AND flights.day = 29 AND flights.hour = (SELECT MIN(hour) FROM flights WHERE day = 29 AND month = 7 AND year = 2023)
AND bakery_security_logs.year = 2023 AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND bakery_security_logs.hour = 10 AND activity = 'exit' AND bakery_security_logs.minute < 25
