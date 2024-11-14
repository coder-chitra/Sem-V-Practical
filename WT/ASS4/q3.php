<!DOCTYPE html>
<html>
<head>
    <title>Check Prime Number</title>
</head>
<body>

    <h1>Checking Whether Number is Prime or not</h1>

    <form method="post" action="q3.php">
        
        <label for="number">Enter a number :</label>
        <input type="number" id="number" name="number" required>
        
        <button type="submit">Click to Check</button>
    </form>

    <?php
    // Check if the form is submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        // Get the number input by the user
        $number = $_POST["number"];
       
        function isPrime($number) {
            $flag = true;
            if($number <= 1) {
                $flag = false;
            }
            else {
                for($i = 2; $i <= $number/2; $i++) {
                    if($number % $i == 0) {
                        $flag = false;
                    }
                }
            }

            return $flag;
        }

        if(isPrime($number)) {
            echo "<h3>$number is Prime<h3>";
        }
        else {
            echo "<h3>$number is not Prime<h3>";
        }
    }
    ?>

</body>
</html>
