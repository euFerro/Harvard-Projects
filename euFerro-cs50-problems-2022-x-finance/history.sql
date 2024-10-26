CREATE TABLE history(
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    date_time DATE NOT NULL,
    user_id INTEGER NOT NULL,
    stock varchar(45) NOT NULL,
    symbol varchar(5) NOT NULL,
    quantity NUMERIC(15) NOT NULL,
    single_price NUMERIC(10) NOT NULL,
    total_price NUMERIC(10) NOT NULL,
    FOREIGN KEY(user_id) REFERENCES users(id)
);

-- ALTERATION
ALTER TABLE history ADD transaction_type varchar(5);

