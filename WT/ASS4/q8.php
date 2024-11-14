<!DOCTYPE html>
<html>
<head>
    <title>Calculate Sum of Digit</title>
</head>
<body>

    <h1>Calculate Sum of Digit</h1>

    <form method="post" action="q8.php">
        
        <label for="number">Enter a Number :</label>
        <input type="number" id="number" name="number" required>
        
        <button type="submit">Click to Calculate</button>
    </form>

    <?php
    // Check if the form is submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        // Get the number input by the user
        $number = $_POST["number"];
       
        $copy = $number;
        $sum = 0;

        while($copy > 0) {
            $sum += ($copy % 10);
            $copy = intdiv($copy,10);
        }

        echo "<h3>Sum of Digit of $number = $sum</h3>";
    }
    ?>

</body>
</html>
