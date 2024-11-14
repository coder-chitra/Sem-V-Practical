<!DOCTYPE html>
<html>
<head>
    <title>Swapping of Number</title>
</head>
<body>

    <h1>Swapping of Number without 3rd Variable</h1>

    <form method="post" action="q2.php">
        
        <label for="number1">Enter a number 1:</label>
        <input type="number" id="number1" name="number1" required>

        <label for="number2">Enter a number 2:</label>
        <input type="number" id="number2" name="number2" required>
        
        <button type="submit">Swap</button>
    </form>

    <?php
    // Check if the form is submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        // Get the number input by the user
        $number1 = $_POST["number1"];
        $number2 = $_POST["number2"];
        // $is_negative = $number < 0; // Check if the number is negative
            // $number = abs($number);  // Take the absolute value for reversing digits

        // Function to reverse the given number
        function swapNumbers($number1,$number2) {

            
            echo "<h2>Original Number1: $number1</h2>";
            echo "<h2>Original Number2: $number2</h2>";

            $number1 = $number1 ^ $number2;
            $number2 = $number1 ^ $number2;
            $number1 = $number1 ^ $number2;
            
            echo "<h2>After Swap: </h2>";
            echo "<h2>Original Number1: $number1</h2>";
            echo "<h2>Original Number2: $number2</h2>";
            return;
        }

        swapNumbers($number1,$number2);
    }
    ?>

</body>
</html>
