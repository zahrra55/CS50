import os
from sqlite3 import IntegrityError
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


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
    user_id = session["user_id"]

    stock_data = db.execute(
        "SELECT symbol, SUM(shares) AS total_shares, MAX(price) AS price, SUM(shares * price) AS total_price FROM purchase WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0;", user_id)

    # Get user's current cash balance
    user_data = db.execute("SELECT cash FROM users WHERE id = ?", user_id)

    if not user_data:
        return apology("User not found", 403)

    account_data = db.execute(
        "SELECT SUM(shares * price) AS paid FROM purchase WHERE user_id = ?", user_id)

    total_cash = user_data[0]["cash"]

    if account_data[0]['paid']:
        total_cash = account_data[0]['paid'] + user_data[0]['cash']

    stock_data = format_stock_prices(stock_data)

    return render_template("index.html", stocks=stock_data, cash=usd(user_data[0]['cash']), total=usd(total_cash))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Must provide stock symbol", 400)

        symbol = symbol.strip().upper()

        shares = request.form.get("shares")
        if not shares or not shares.isdigit():
            return apology("Must provide a positive integer number of shares", 400)

        shares = int(shares)

        if shares <= 0:
            return apology("Must provide a positive integer number of shares", 400)

        # Lookup stock information
        stock = lookup(symbol)
        if not stock:
            return apology("Stock symbol not found", 400)

        user_id = session["user_id"]

        # user_cash_result
        user_data = db.execute("SELECT cash FROM users WHERE id = ?", user_id)

        if not user_data:
            return apology("User not found", 403)

        total_cost = stock["price"] * shares
        user_cash = user_data[0]["cash"]

        # Check if user can afford the purchase
        if user_cash < total_cost:
            return apology("Cannot afford this purchase", 400)

        # Insert purchase into purchase table
        db.execute("INSERT INTO purchase (user_id, symbol, shares, price, total_price) VALUES (?, ?, ?, ?, ?)",
                   user_id, stock["symbol"].upper(), shares, stock["price"], total_cost)

        # Update user's cash balance
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_cost, user_id)

        # Flash success message and redirect
        flash("Stock purchased successfully!")

        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    purchase = db.execute("SELECT * FROM purchase WHERE user_id = ?", session["user_id"])
    purchase = format_stock_prices(purchase)
    print(purchase)

    return render_template("history.html", purchase=purchase)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 400)

        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        # Get and sanitize user input
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Must provide stock symbol", 400)

        symbol = symbol.strip()  # Trim whitespace

        # Lookup stock information
        stock = lookup(symbol)
        if not stock:
            return apology("Stock symbol not found", 400)

        return render_template("quoted.html",  price=usd(stock['price']), symbol=stock['symbol'])

    # Render the quote form
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    if request.method == "POST":
        # Get form data and sanitize input
        username = request.form.get("username").strip()
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Validate input
        if not username:
            return apology("must provide username", 400)
        if not password:
            return apology("must provide password", 400)
        if not confirmation:
            return apology("must verify the password", 400)
        if password != confirmation:
            return apology("passwords do not match", 400)

        duplicate = db.execute("SELECT id FROM users WHERE username = ?", username)

        if len(duplicate) >= 1:
            return apology("Username already exists")

        # Hash the password
        hash = generate_password_hash(password)

        # Insert user into database
        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
        except IntegrityError:
            return apology("username already exists", 400)

        # Log the user in
        user_id = db.execute("SELECT id FROM users WHERE username = ?", username)[0]["id"]
        session["user_id"] = user_id

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    user_id = session["user_id"]
    if request.method == "POST":
        symbol = request.form.get("symbol").strip().upper()
        shares = float(request.form.get("shares"))

        if int(shares) <= 0:
            return apology("Must provide a positive integer number of shares", 400)

        result = db.execute(
            "SELECT SUM(shares) AS total_shares FROM purchase WHERE user_id = ? AND symbol = ? GROUP BY symbol", user_id, symbol)

        if not result or result[0]["total_shares"] is None:
            return apology("You do not own this stock", 400)

        user_shares = result[0]["total_shares"]
        if shares > float(user_shares):
            return apology("Too many shares", 400)

        stock = lookup(symbol)

        total_price = stock["price"] * shares
        if not stock:
            return apology("Stock data unavailable, try again later.", 400)

        db.execute("INSERT INTO purchase (user_id, symbol, shares, price, transaction_type, total_price) VALUES (?, ?, ?, ?, ?, ?)",
                   user_id, symbol, -shares, stock["price"], "sell", total_price)

        # Update the user's cash balance based on the sale
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?",
                   stock["price"] * shares, user_id)

        flash("Stock sold successfully!")
        return redirect("/")

    stocks = db.execute(
        "SELECT symbol, SUM(shares) AS total_shares FROM purchase WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0", user_id)

    return render_template("sell.html", stocks=stocks)


@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    """Allow users to change their password"""
    if request.method == "POST":
        current_password = request.form.get("current_password")
        new_password = request.form.get("new_password")
        confirmation = request.form.get("confirmation")

        # Validate password inputs
        if not current_password or not new_password or new_password != confirmation:
            return apology("Passwords do not match or missing fields", 400)

        # Retrieve user info from the database
        user = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

        # Verify current password
        if not check_password_hash(user[0]["hash"], current_password):
            return apology("Incorrect current password", 400)

        # Update password
        hashed_new_password = generate_password_hash(new_password)
        db.execute("UPDATE users SET hash = ? WHERE id = ?",
                   hashed_new_password, session["user_id"])

        flash("Password changed successfully!")
        return redirect("/")

    return render_template("change_password.html")


def format_stock_prices(SD):
    """Format Stock prices"""

    for _, stock in enumerate(SD):
        stock['price'] = usd(stock['price'])
        stock['total_price'] = usd(stock['total_price'])

    return SD
