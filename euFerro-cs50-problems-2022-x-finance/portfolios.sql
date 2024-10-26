CREATE TABLE portfolios(
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    user_id INTEGER NOT NULL,
    symbol varchar(5) NOT NULL,
    quantity NUMERIC(15) NOT NULL,
    FOREIGN KEY(user_id) REFERENCES users(id)
);