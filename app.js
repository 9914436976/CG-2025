const express = require("express");
const bodyParser = require("body-parser");
const axios = require("axios");
const cors = require("cors");

const app = express();
app.use(cors()); // Enable CORS
app.use(bodyParser.json());
app.use(express.static(__dirname));

// Replace with your actual RapidAPI key
const RAPIDAPI_KEY = "489e6fd068msh783fb79ca7c92bfp103cbbjsna38cc4cfe282";

// Judge0 API Configuration
const JUDGE0_API_URL = "https://judge0-ce.p.rapidapi.com/submissions";
const JUDGE0_HEADERS = {
    "X-RapidAPI-Key": RAPIDAPI_KEY,
    "X-RapidAPI-Host": "judge0-ce.p.rapidapi.com",
    "Content-Type": "application/json"
};

// Language IDs for Judge0 API
const JUDGE0_LANGUAGES = {
    cpp: 54,  // C++ (GCC 9.2.0)
    java: 62, // Java (OpenJDK 13.0.1)
    python: 71 // Python (3.8.1)
};

console.log(__dirname)

app.get("/", function (req, res) {
    res.sendFile(__dirname + "/frontend/index.html");
});

app.post("/compile", async function (req, res) {
    const { code, lang } = req.body;  // 🔹 Removed 'input' from request body

    if (!code) {
        return res.status(400).json({ error: "No code provided" });
    }

    const languageId = JUDGE0_LANGUAGES[lang];

    if (!languageId) {
        return res.status(400).json({ error: "Unsupported language" });
    }

    try {
        // Submit Code to Judge0 API (Without stdin)
        const submissionResponse = await axios.post(
            `${JUDGE0_API_URL}?base64_encoded=false&wait=true`,
            {
                source_code: code,
                language_id: languageId,  // 🔹 Removed 'stdin' from request
            },
            { headers: JUDGE0_HEADERS }
        );

        const result = submissionResponse.data;

        // Return the output or errors
        if (result.stdout) {
            res.json({ output: result.stdout });
        } else if (result.stderr) {
            res.json({ output: "Error: " + result.stderr });
        } else if (result.message) {
            res.json({ output: "Message: " + result.message });
        } else {
            res.json({ output: "Execution completed with no output." });
        }
    } catch (error) {
        res.status(500).json({
            error: "Execution failed",
            details: error.response ? error.response.data : error.message
        });
    }
});

module.exports = app