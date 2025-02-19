const express = require("express");
const bodyParser = require("body-parser");
const compiler = require("compilex");

const app = express();
const options = { stats: true };  // Enable stats for compilex
compiler.init(options);

// Use body-parser to parse incoming JSON
app.use(bodyParser.json());  

// Serve CodeMirror files
app.use("/codemirror-5.65.18", express.static("C:/Users/hp/Desktop/codemirror/codemirror-5.65.18"));

// Serve the frontend HTML file
app.get("/", function (req, res) {
    res.sendFile("C:/Users/hp/Desktop/codemirror/index.html");
});

// Handle code compilation request
app.post("/compile", function (req, res) {
    const code = req.body.code;
    const input = req.body.input;  // Retrieve input
    const lang = req.body.lang.toLowerCase();  // Convert language to lowercase

    if (!code) {
        return res.status(400).send({ error: "No code provided" });
    }

    let envData = { OS: "windows" };

    // Handle C++ Compilation
    if (lang === "cpp") {
        envData.cmd = "g++";  // Specify g++ explicitly
        compiler.compileCPPWithInput(envData, code, input || "", function (data) {
            res.send(data);
        });
    }
    // Handle Java Compilation
    else if (lang === "java") {
        compiler.compileJavaWithInput(envData, code, input || "", function (data) {
            res.send(data);
        });
    }
    // Handle Python Compilation
    else if (lang === "python") {
        compiler.compilePythonWithInput(envData, code, input || "", function (data) {
            res.send(data);
        });
    } else {
        res.status(400).send({ error: "Unsupported language" });
    }
});

// Start server on port 8000
app.listen(8000, function () {
    console.log("Server running on http://localhost:8000");
});
