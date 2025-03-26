-- Keep a log of any SQL queries you execute as you solve the mystery.

-- To see the crime description:
SELECT description
FROM crime_scene_reports
WHERE street = "Humphrey Street"
AND month = 7
AND day = 28;

-- Let's see what people say in the interviews
 SELECT transcript
 FROM interviews
 WHERE transcript LIKE '%bakery%';

--1> within ten minutes of the theft the thief got into a car after about 10min
-- it happend at 10:15 so it must be between 10:15 and 10:25
SELECT *
FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.minute BETWEEN 15 AND 25
AND bakery_security_logs.day = 28
AND bakery_security_logs.month = 7
and bakery_security_logs.hour = 10;
-- The names are: Bruce, Barry, Luca, Sofia, Iman, Diana and Kelsey

--2> by the ATM on Leggett Street someone saw the thief there withdrawing some money
--lets check poeple who withdrawed money at that day
SELECT people.name,
atm_transactions.transaction_type,
atm_transactions.atm_location,
atm_transactions.amount,
atm_transactions.day,
atm_transactions.month
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE atm_transactions.atm_location LIKE '%Leggett Street%'
AND atm_transactions.day = 28
AND atm_transactions.month = 7
AND atm_transactions.transaction_type = "withdraw";
-- The names are: Bruce, Diana, Brooke, Kenny, Iman, Luca, Taylor and Benista.

--The common names so far are: Bruce, Diana, Iman, and Luca.

--3> the thief called someone for less than a minute!
SELECT people.name,people.phone_number,
rec.name,rec.phone_number,
phone_calls.caller,phone_calls.receiver,phone_calls.duration,
people.passport_number,people.license_plate
FROM phone_calls
JOIN people ON people.phone_number = phone_calls.caller
JOIN people as rec ON rec.phone_number = phone_calls.receiver
WHERE day = 28 AND month = 7 AND duration < 60
ORDER BY duration;
/* The Output:
Caller -> Receiver
Kelsey -> Larry
Carina -> Jacqueline
Taylor -> James
Bruce  -> Robin
Diana  -> Philip
Kelsey -> Melissa
Sofia  -> Jack
Benista-> Anna
Kenny  -> Doris

the only matches are:
Bruce → Robin
Diana → Philip
Other calls that don’t match.

*/

--4> The thief then asked the person on the other end of the phone to purchase the earliest flight ticket out of Fiftyville tomorrow
-- Let's check the flight tickets
SELECT * FROM flights
JOIN airports ON flights.origin_airport_id = airports.id
WHERE airports.city = "Fiftyville" AND day = 29
ORDER BY hour;
-- The earliest flight is origin_airport_id = 8, destination_airport_id = 4 at 08:20

-- Now let's see the destination with the id 4 (the earliest one) and the origion id 8
SELECT people.name,passengers.seat,passengers.passport_number,passengers.flight_id
FROM passengers
JOIN flights ON flights.id = passengers.flight_id
JOIN people ON people.passport_number = passengers.passport_number
WHERE flights.destination_airport_id = 4
AND flights.origin_airport_id = 8
AND flights.day = 29
AND flights.hour = 8
and flights.minute = 20;
-- The names are: Doris, Sofia, Bruce, Edward, Kelsey, Taylor, Kenny and Luca.
--Comparing with (Bruce, Diana, Iman, Luca), Bruce and Luca were on this flight.

-- Destination city
SELECT full_name,city
FROM airports
WHERE id = (
SELECT destination_airport_id FROM flights
WHERE destination_airport_id = 4);
--It is  LaGuardia Airport | New York City

/*
SO...
The strongest match of (security logs, ATM withdrawal, short phone call, and flight) is Bruce.
and Bruce only called Robin
and the trip is to New Yourk City
*/
