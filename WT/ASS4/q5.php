<!DOCTYPE html>
<html>
<head>
    <title>Check Even Odd</title>
</head>
<body>

    <h1>Checking Even Odd</h1>

    <form method="post" action="q5.php">
        
        <label for="number">Enter a number :</label>
        <input type="number" id="number" name="number" required>
        
        <button type="submit">Click to Check</button>
    </form>

    <?php
    // Check if the form is submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        // Get the number input by the user
        $number = $_POST["number"];
       
        function isEven($number) {
            
            if($number % 2 == 0) {
               return true;
            }
            else {
               return false;
            }
        }
        if(isEven($number)) {
            echo "<h3>$number is Even</h3>";
        }
        else {
            echo "<h3>$number is Odd</h3>";
        }
    }
    ?>

</body>
</html>
