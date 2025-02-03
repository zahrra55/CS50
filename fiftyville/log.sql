-- Keep a log of any SQL queries you execute as you solve the mystery.

-- To see the crime description:
SELECT description
FROM crime_scene_reports
WHERE street = "Humphrey Street"
AND month = 7
AND day = 28;

-- To see who was in the bakery at that time:
SELECT * FROM
bakery_security_logs
WHERE minute BETWEEN 10 AND 20
AND day = 28
AND month = 7
and hour = 10;

-- Now let us see if People table has the criminal:
SELECT *
FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.minute BETWEEN 10 AND 20
AND bakery_security_logs.day = 28
AND bakery_security_logs.month = 7
and bakery_security_logs.hour = 10;

-- Let's see what people say in the interviews
 SELECT transcript
 FROM interviews
 WHERE transcript LIKE '%bakery%';

-- Someone mentioned seeing the thief withdrawing some money.
 SELECT *
 FROM atm_transactions
 WHERE atm_location LIKE '%Humphrey%'
 AND day = 28
 AND month = 7
 AND transaction_type = "withdraw";

-- heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow
-- Let's check the flight tickets
SELECT * FROM flights
JOIN airports ON flights.origin_airport_id = airports.id
WHERE airports.city = "Fiftyville"
ORDER BY hour,minute;

-- Now let's see the destination with the id 2
SELECT passengers.seat,passengers.passport_number,passengers.flight_id
FROM passengers
JOIN flights ON flights.id = passengers.flight_id
JOIN airports ON flights.id = airports.id
WHERE flights.destination_airport_id = 2
AND airports.city = "Fiftyville";

--
SELECT * FROM phone_calls
WHERE day = 28 AND month = 7
ORDER BY duration;

--The longer duration
SELECT * FROM people
WHERE phone_number = "(544) 555-8087";

--checking people
SELECT * FROM people
WHERE phone_number = "(544) 555-8087";
-- THE CALLER IS WALTER: (544) 555-8087
-- THE RESEVER IS LUCA: (389) 555-5198

SELECT people.name, atm_transactions.transaction_type,
atm_transactions.atm_location,
atm_transactions.day, atm_transactions.month
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE people.id = 467400;
-- Luca withdrawed at Leggett Street in 28 July!!!

SELECT * FROM passengers
JOIN people ON passengers.passport_number = people.passport_number
JOIN flights ON flights.id = passengers.flight_id
--JOIN atm_transactions ON atm_transactions.id = people.id
WHERE passengers.passport_number = 8496433585
AND flights.destination_airport_id = 2;

SELECT * FROM people where name = "Luca" OR name = "Walter";
--Luca passport number = 8496433585
--Walter passport number = 4223654265

SELECT * FROM passengers
WHERE passport_number = 8496433585 OR passport_number = 4223654265;


SELECT passengers.flight_id, flights.destination_airport_id
FROM passengers
JOIN flights ON passengers.flight_id = flights.id
WHERE passengers.passport_number = 8496433585;

-- Destination city
SELECT full_name,city
FROM airports
WHERE id = (
SELECT destination_airport_id FROM flights
JOIN passengers ON flights.id = passengers.flight_id
WHERE passengers.passport_number = 8496433585);


--all in one
SELECT flights.id AS flight_number, airports.full_name AS destination_airport, airports.city AS destination_city
FROM passengers
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON flights.destination_airport_id = airports.id
WHERE passengers.passport_number = 8496433585;

--the escap city
SELECT airports.city
FROM airports
JOIN flights ON airports.id = flights.destination_airport_id
WHERE flights.id = (
    SELECT flight_id
    FROM passengers
    WHERE passport_number = 8496433585
);

SELECT people.name
FROM people
WHERE phone_number = '(544) 555-8087';


SELECT account_number
FROM atm_transactions
WHERE month = 7
AND day = 28
AND atm_location LIKE '%Humphrey%'
AND transaction_type = 'withdraw';


