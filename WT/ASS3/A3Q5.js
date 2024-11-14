function handleSubmit() {
    // Get the input values
    const name = document.getElementById('name').value.trim();
    const age = parseInt(document.getElementById('age').value);
    const mobile = document.getElementById('mobile').value.trim();

    // Validate inputs
    if (!name) {
        alert("Student Name cannot be empty.");
        return;
    }

    if (age < 1 || age > 18) {
        alert("Student Age must be between 1 and 18.");
        return;
    }

    if (mobile.length !== 10 || isNaN(mobile)) {
        alert("Mobile No must be 10 digits long and cannot be empty.");
        return;
    }

    // If all validations pass, display the result
    const resultDiv = document.getElementById('result');
    resultDiv.textContent = `Student Name: ${name}, Age: ${age}, Mobile No: ${mobile}`;
}

