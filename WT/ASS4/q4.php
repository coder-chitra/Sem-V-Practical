<!DOCTYPE html>
<html>
<head>
    <title>Factorial of a Number</title>
</head>
<body>

    <h1>Calculating Factorial of a Number</h1>

    <form method="post" action="q4.php">
        
        <label for="number">Enter a number :</label>
        <input type="number" id="number" name="number" required>
        
        <button type="submit">Click to Calculate</button>
    </form>

    <?php
    // Check if the form is submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        // Get the number input by the user
        $number = $_POST["number"];
       
        function factorial($number) {
            
            if($number < 0) {
               echo "<h3>Enter Valid Integer >= 0</h3>";
            }
            else {
                $factorial = 1;

                for($i = 1; $i <= $number; $i++) {
                    $factorial *= $i;
                }

                echo "<h3> Factorial of $number = $factorial</h3>";
            }
        }

        factorial($number);
    }
    ?>

</body>
</html>
