import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
from has_letters import has_letters  # My custom function

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    holdings = db.execute("SELECT * FROM portfolios WHERE user_id = ?", session["user_id"])
    print(holdings)

    total_hold = 0

    for hold in holdings:
        stock = lookup(hold["symbol"])
        hold["price"] = usd(stock["price"])
        hold["amount"] = hold["quantity"] * stock["price"]
        total_hold += float(hold["amount"])
        # Convert to usd format
        hold["amount"] = usd(hold["amount"])

    wallet = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

    cash = wallet[0]["cash"]
    total = usd(total_hold + float(cash))
    hold = usd(total_hold)
    cash = usd(cash)

    return render_template("index.html", holdings=holdings, cash=cash, hold=hold, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "GET":
        return render_template("buy.html", not_symbol=False, not_quant=False)

    if request.method == "POST":

        # Validation variables
        stock_symbol = request.form.get("symbol")
        quantity = request.form.get("shares")
        stock = lookup(stock_symbol)

        # User variables
        user_id = session["user_id"]
        user = db.execute("SELECT * FROM users WHERE id = ?", user_id)
        user_cash = user[0]["cash"]

        # Check if input fields's values aren't empty
        if not stock_symbol and not quantity:
            return render_template("buy.html", invalid_stock=True, invalid_quant=True, msg="Fill out this field"), 400

        if not stock_symbol and quantity:
            return render_template("buy.html", invalid_stock=True, msg="Fill out this field"), 400

        if stock_symbol and not quantity:
            return render_template("buy.html", invalid_quant=True, msg="Fill out this field"), 400

        # Validation's bools
        invalid_quantity = str.isalpha(quantity) or has_letters(quantity) and any(str.isdigit(char)
                                                                                  for char in quantity) or float(quantity) <= 0
        invalid_stock = stock == None
        # End

        if invalid_stock and invalid_quantity:
            return render_template("buy.html", invalid_stock=True, invalid_quant=True, msg="Invalid"), 400

        if invalid_stock:
            return render_template("buy.html", invalid_stock=True, msg="Invalid"), 400

        if invalid_quantity:
            return render_template("buy.html", invalid_quant=True, msg="Invalid"), 400

        total = int(quantity) * float(stock["price"])

        # Check if user can buy stock
        if total > float(user_cash):
            return render_template("buy.html", invalid_quant=True, msg="Can't buy a value greater than your cash"), 400

        new_balance = float(user_cash) - float(total)

        # Register purchase
        db.execute("INSERT INTO history(date_time, transaction_type, user_id, stock, symbol, quantity, single_price, total_price) VALUES(DATETIME(), ?, ?, ?, ?, ?, ?, ?)",
                   "buy", int(user_id), stock["name"], stock["symbol"], int(quantity), float(stock["price"]), float(total))

        # User already have this stock?
        list = db.execute("SELECT symbol FROM portfolios WHERE user_id = ? AND symbol = ?",
                          session["user_id"], stock_symbol.upper())

        if len(list) != 1:  # Doesn't have
            db.execute("INSERT INTO portfolios(user_id, symbol, quantity) VALUES(?,?,?)",
                       session["user_id"], stock_symbol.upper(), quantity)
        else:
            db.execute("UPDATE portfolios SET quantity = quantity + ? WHERE user_id = ? AND symbol = ?",
                       quantity, session["user_id"], stock["symbol"].upper())

        # Update cash balance
        db.execute("UPDATE users SET cash = ? WHERE id = ?", float(new_balance), int(user_id))

    return render_template("buy.html",bought=True, name=stock["name"], symbol=stock["symbol"], quantity=quantity, price=usd(stock["price"]), total=usd(total), money=usd(user_cash - total))


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    history = db.execute("SELECT * FROM history WHERE user_id = ?", session["user_id"])
    print(history)

    for register in history:
        register["single_price"] = usd(register["single_price"])
        register["total_price"] = usd(register["total_price"])

    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    # session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "GET":
        return render_template("quote.html", not_found=False, search=False)

    if request.method == "POST":

        symbol = request.form.get("symbol")
        stock = lookup(symbol)

        if stock == None:
            return render_template("quote.html", not_found=True, search=False), 400

        print(stock)
        stock["price"] = usd(stock["price"])

    return render_template("quote.html", stock=stock, search=True), 200


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "GET":
        return render_template("register.html")

    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        if not request.form.get("password") or not request.form.get("confirmation"):
            return apology("must provide password", 400)

        # look for username in database
        username = request.form.get("username")
        queried_username = db.execute("SELECT * FROM users WHERE username = ?;", username)
        if len(queried_username) > 0:
            return apology("username already taken", 400)

        # Gets both passwords
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Check if both passwords are different
        if not password == confirmation:
            return apology("passwords don't match", 400)

        # Hash password
        password_hash = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)
        # Register user into database
        db.execute("INSERT INTO users(username, hash) values(?, ?);", username, password_hash)

    return render_template("success.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    ownedShares = db.execute("SELECT symbol FROM portfolios WHERE user_id = ?", session["user_id"])
    print(ownedShares)

    if request.method == "GET":
        return render_template("sell.html", ownedShares=ownedShares)

    if request.method == "POST":

        # Validation variables
        stock_symbol = request.form.get("symbol")
        quantity = request.form.get("shares")
        stock = lookup(stock_symbol)

        # User variables
        user_id = session["user_id"]
        user = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user[0]["cash"]
        print(user)

        # Check if input fields's values aren't empty
        if not stock_symbol and not quantity:
            return render_template("sell.html", invalid_stock=True, invalid_quant=True, msg="Fill out this field", ownedShares=ownedShares), 400

        if not stock_symbol and quantity:
            return render_template("sell.html", invalid_stock=True, msg="Fill out this field", ownedShares=ownedShares), 400

        if stock_symbol and not quantity:
            return render_template("sell.html", invalid_quant=True, msg="Fill out this field", ownedShares=ownedShares), 400

        # Validation's bools
        invalid_quantity = str.isalpha(quantity) or has_letters(quantity) and any(str.isdigit(char)
                                                                                  for char in quantity) or float(quantity) <= 0
        invalid_stock = stock == None
        # End

        if invalid_stock and invalid_quantity:
            return render_template("sell.html", invalid_stock=True, invalid_quant=True, msg="Invalid", ownedShares=ownedShares), 400

        if invalid_stock:
            return render_template("sell.html", invalid_stock=True, msg="Invalid", ownedShares=ownedShares), 400

        if invalid_quantity:
            return render_template("sell.html", invalid_quant=True, msg="Invalid", ownedShares=ownedShares), 400

        total = int(quantity) * float(stock["price"])

        # Check if user has the stock and get it's share amount
        current_hold = db.execute(
            "SELECT * FROM portfolios WHERE user_id = ? AND symbol = ?", user_id, stock_symbol.upper())

        # Check if user has the stock
        if len(current_hold) != 1:
            return render_template("sell.html", invalid_stock=True, msg="You don't have this stock", ownedShares=ownedShares), 400

        hold_quantity = current_hold[0]["quantity"]

        # Check if user can sell stock
        if int(quantity) > hold_quantity:
            return render_template("sell.html", invalid_quant=True, msg="Can't sell more shares than you have", ownedShares=ownedShares), 400

        new_balance = float(user_cash) + float(total)

        # Register sale
        db.execute("INSERT INTO history(date_time, transaction_type, user_id, stock, symbol, quantity, single_price, total_price) VALUES(DATETIME(), ?, ?, ?, ?, ?, ?, ?)",
                   "sell", int(user_id), stock["name"], stock["symbol"], int(quantity), float(stock["price"]), float(total))

        # Update portifolio
        db.execute("UPDATE portfolios SET quantity = quantity - ? WHERE user_id = ? AND symbol = ?",
                   quantity, user_id, stock_symbol.upper())

        # Update cash balance
        db.execute("UPDATE users SET cash = ? WHERE id = ?", float(new_balance), int(user_id))

    return render_template("sell.html", sold=True, name=stock["name"], symbol=stock["symbol"], quantity=quantity, price=usd(stock["price"]), total=usd(total), money=usd(user_cash + total), ownedShares=ownedShares)
