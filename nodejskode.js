const express = require('express');
const bodyParser = require('body-parser');
const fs = require('fs');  // Import the fs (file system) module
const app = express();
const port = 3000; // Port on which the server will listen

// Middleware to parse URL-encoded data (form data)
app.use(bodyParser.urlencoded({ extended: true }));

// Route to handle incoming POST requests
app.post('/submit_data', (req, res) => {
  const ldrValue = req.body.ldrValue;
  const doorStatus = req.body.doorStatus;

  // Prepare the data in a readable format
  const data = `LDR Value: ${ldrValue}, Door Status: ${doorStatus}\n`;

  // Append the data to a file called 'sensor_data.txt'
  fs.appendFile('sensor_data.txt', data, (err) => {
    if (err) {
      console.error('Error writing to file:', err);
      return res.status(500).send('Error saving data to file');
    }
    console.log('Data saved to sensor_data.txt');
  });

  // Respond back with a success message
  res.send('Data received and saved successfully!');
});

// Start the server
app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}`);
});
