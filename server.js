const express = require('express');
const bodyParser = require('body-parser');
const { execFile } = require('child_process');

const app = express();
app.use(bodyParser.json());
const PORT = 3000;

app.post('/verify', (req, res) => {
    const { username, password } = req.body;
    execFile('./authenticator', [username, password], (error, stdout, stderr) => {
        if (error) {
            console.error(`exec error: ${error}`);
            return res.status(500).json({ message: 'Server error' });
        }
        return res.json({ message: stdout.trim() });
    });
});

app.listen(PORT, () => {
    console.log(`Server running on http://localhost:${PORT}`);
});
