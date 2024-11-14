<!DOCTYPE html>
<html>
<head>
    <title>Calculate Fibonnaci Series</title>
</head>
<body>

    <h1>Calclating Fibonacci Series upto N terms</h1>

    <form method="post" action="q6.php">
        
        <label for="n">Enter a N :</label>
        <input type="number" id="n" name="n" required>
        
        <button type="submit">Click to Calculate</button>
    </form>

    <?php
    // Check if the form is submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        // Get the number input by the user
        $n = $_POST["n"];
       
        function fibonacci($n) {
            
            if($n <= 0) {
                echo "<br><b>Enter a Valid Integer > 0</b>";
                return;
            }
            
            $term1 = 0;
            $term2 = 1;
            $term3 = $term1 + $term2;
            echo "<br><br>";
            echo "<b>1st $n terms of fibonacci series are : </b>";
            while($n > 0) {
                echo "<b>$term1  </b>";
                $term1 = $term2;
                $term2 = $term3;
                $term3 = $term1 + $term2;
                $n--;
            }
        }
        fibonacci($n);
    }
    ?>

</body>
</html>
