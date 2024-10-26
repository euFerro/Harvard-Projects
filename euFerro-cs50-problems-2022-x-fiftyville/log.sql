-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Looked at the crime reports at the day of the crime
SELECT * FROM crime_scene_reports WHERE month = 7 AND day = 28;

-- Checked the interview of the three witness at the samee day
SELECT * FROM interviews WHERE day = 28 AND month = 7;

-- Looked at atm_transactions in the day 28
 SELECT * FROM atm_transactions WHERE atm_location = 'Leggett Street' AND transaction_type = 'withdraw' AND day = 28;

 -- Security logs at with the witness descriptions
 SELECT * FROM bakery_security_logs WHERE day = 28 AND hour = 10 AND minute BETWEEN 15 AND 30;

 -- Airport history in the description
SELECT * FROM flights WHERE day = 29;
-- Thief's origin city
SELECT city FROM airports AS a JOIN flights AS f ON a.id = f.origin_airport_id WHERE f.day = 29 AND hour = 8;
-- Thief's destination city
SELECT city FROM airports AS a JOIN flights AS f ON a.id = f.destination_airport_id WHERE f.day = 29 AND hour = 8;

SELECT * FROM phone_calls WHERE day = 28 AND duration <= 60;
-- Thief's Flight
SELECT * FROM flights WHERE day = 29 AND hour = 8;
-- Passengers of the flight
SELECT * FROM passengers AS p JOIN flights AS f ON f.id = p.flight_id WHERE f.id = 36;

-- Query to find the name in the phone_calls table
-- Caller
SELECT name FROM people AS pp JOIN phone_calls AS pc ON pp.phone_number = pc.caller WHERE day = 28 AND duration <= 60;
-- Receiver
SELECT name FROM people AS pp JOIN phone_calls AS pc ON pp.phone_number = pc.receiver WHERE day = 28 AND duration <= 60;

-- Checking people that called and are on the plane
SELECT name FROM people AS pp JOIN phone_calls AS pc ON pp.phone_number = pc.caller WHERE pc.day = 28 AND pc.duration <= 60 AND pp.passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36);

-- Checking people that called and are on the plane and car exit parking lot
SELECT * FROM people AS pp JOIN phone_calls AS pc ON pp.phone_number = pc.caller JOIN bakery_security_logs AS bsl ON bsl.license_plate = pp.license_plate WHERE pc.day = 28 AND duration <= 60 AND bsl.day = 28 AND bsl.activity = 'exit' AND bsl.hour = 10 AND bsl.minute BETWEEN 15 AND 30 AND pp.passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36);

-- People that where in the plane exit parking lot in the bakery between 10:15 am to 10:30 and made atm transaction at lagget street
SELECT DISTINCT pp.id, pp.name, pp.phone_number FROM people AS pp JOIN phone_calls AS pc ON pp.phone_number = pc.caller JOIN bakery_security_logs AS bsl ON bsl.license_plate = pp.license_plate JOIN bank_accounts AS ba ON ba.person_id = pp.id JOIN atm_transactions AS atm ON atm.account_number = ba.account_number WHERE pc.day = 28 AND duration <= 60 AND bsl.day = 28 AND bsl.activity = 'exit' AND bsl.hour = 10 AND bsl.minute BETWEEN 15 AND 30 AND atm.atm_location = 'Leggett Street' AND pp.passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36);

-- Verifying that the thief was Bruce
-- Phone Calls
SELECT * FROM phone_calls AS pc JOIN people AS pp ON pc.caller = pp.phone_number WHERE pp.name = 'Bruce' AND pc.duration <= 60 AND pc.day = 28;
-- Parking Lot
SELECT * FROM bakery_security_logs AS bsl JOIN people AS pp ON bsl.license_plate = pp.license_plate WHERE pp.name = 'Bruce' AND bsl.day = 28 AND bsl.activity = 'exit';
-- In The Flight
SELECT * FROM flights AS fl JOIN passengers AS ps ON fl.id = ps.flight_id JOIN people AS pp ON pp.passport_number = ps.passport_number WHERE pp.name = 'Bruce' AND fl.id = 36;
-- ATM
SELECT * FROM atm_transactions AS atm JOIN bank_accounts AS ba ON atm.account_number = ba.account_number JOIN people AS pp ON pp.id = ba.person_id WHERE pp.name = 'Bruce' AND atm.atm_location = 'Leggett Street';

-- Who was the accomplice?
SELECT * FROM people WHERE phone_number = '(375) 555-8161';
