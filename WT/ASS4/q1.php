<!DOCTYPE html>
<html>
<head>
    <title>Reverse a Number</title>
</head>
<body>

    <h1>Reverse a Number using PHP</h1>

    <form method="post" action="q1.php">
        <label for="number">Enter a number:</label>
        <input type="number" id="number" name="number" required>
        <button type="submit">Reverse</button>
    </form>

    <?php
    // Check if the form is submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        // Get the number input by the user
        $number = $_POST["number"];
        $is_negative = $number < 0; // Check if the number is negative
            $number = abs($number);  // Take the absolute value for reversing digits

        // Function to reverse the given number
        function reverseNumber($num) {
            $rev_num = 0;

            // Extract the digits from the number and reverse them
            while ($num > 0) {
                $last_digit = $num % 10;
                $rev_num = ($rev_num * 10) + $last_digit;
                $num = (int)($num / 10);
            }

            return $rev_num;
        }

        // Display the original and reversed number
        echo "<h2>Original Number: $number</h2>";
        echo "<h2>Reversed Number: " . reverseNumber($number) . "</h2>";
    }
    ?>

</body>
</html>
