<!DOCTYPE html>
<html>
<head>
    <title>Calculate Largest of 3 </title>
</head>
<body>

    <h1>Calclating Largest of 3 Numbers </h1>

    <form method="post" action="q7.php">
        
        <label for="n1">Enter a Number 1 :</label>
        <input type="number" id="n1" name="n1" required> <br><br>
        
        <label for="n2">Enter a Number 2 :</label>
        <input type="number" id="n2" name="n2" required> <br><br>
        
        <label for="n3">Enter a Number 3 :</label>
        <input type="number" id="n3" name="n3" required> <br><br>
        
        <button type="submit">Click to Check</button>
    </form>

    <?php
    // Check if the form is submitted
        if ($_SERVER["REQUEST_METHOD"] == "POST") {
            // Get the number input by the user
            $n1 = $_POST["n1"];
            $n2 = $_POST["n2"];
            $n3 = $_POST["n3"];
            
            if($n1 > $n2 && $n1 > $n3) {
                echo "<h3>Largest Number = $n1</h3>";
            }
            else if($n2 > $n3){
                echo "<h3>Largest Number = $n2</h3>";
            }
            else {
                echo "<h3>Largest Number = $n3</h3>";
            }
        
        }
    ?>

</body>
</html>
