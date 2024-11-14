function removeWhitespace() {
    let str1 = prompt("Enter the first string:");
    let str2 = prompt("Enter the second string:");

    if (str1 !== null && str2 !== null) {
        const cleanedStr1 = str1.replace(/\s+/g, '');
        const cleanedStr2 = str2.replace(/\s+/g, '');
        alert(`String 1 without whitespace: "${cleanedStr1}"\nString 2 without whitespace: "${cleanedStr2}"`);
    }
}

function concatenateStrings() {
    let str1 = prompt("Enter the first string:");
    let str2 = prompt("Enter the second string:");

    if (str1 !== null && str2 !== null) {
        const concatenated = str1 + str2;
        alert(`Concatenated String: "${concatenated}"`);
    }
}

function compareStrings() {
    let str1 = prompt("Enter the first string:");
    let str2 = prompt("Enter the second string:");

    if (str1 !== null && str2 !== null) {
        if (str1 === str2) {
            alert("The strings are equal.");
        } else {
            alert("The strings are not equal.");
        }
    }
}

// Function to keep prompting user for operations
function promptUser() {
    let continuePrompting = true;

    while (continuePrompting) {
        const operation = prompt("Choose an operation:\n1. Remove Whitespace\n2. Concatenate Strings\n3. Compare Strings\n4. Exit");

        switch (operation) {
            case '1':
                removeWhitespace();
                break;
            case '2':
                concatenateStrings();
                break;
            case '3':
                compareStrings();
                break;
            case '4':
                continuePrompting = false;
                alert("Exiting the program.");
                break;
            default:
                alert("Invalid choice. Please select a valid operation.");
                break;
        }
    }
}

// Start prompting the user for operations
promptUser();

