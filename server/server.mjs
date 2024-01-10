import express from 'express';
import fetch from 'node-fetch';
import { SerialPort } from 'serialport';

const app = express();
app.use(express.json());

const portName = 'COM9';

const port = new SerialPort({
  path: portName,
  baudRate: 9600
});

app.post('/sendCommand', async (req, res) => {
  const userInput = req.body.command;

  // Enhanced prompt with examples for few-shot learning
  const prompt = `I am a program that translates natural language instructions into specific commands for a robotic movement. Here are some examples:

  User input: "move in a square"
  Robot instructions: "moveLeft 1000\nmoveForward 1000\nmoveRight 2000\nmoveBackward 2000\nmoveLeft 1000\n"

  User input: "move in a triangle"
  Robot instructions: "moveLeft 1000\nmoveRight 1000\nmoveBackward 1000\n"

  User input: "${userInput}"
  Robot instructions:`;

  // Call ChatGPT API with the enhanced prompt
  const gptResponse = await fetch('https://api.openai.com/v1/engines/davinci-codex/completions', {
    method: 'POST',
    headers: {
      'Authorization': `Bearer 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`,
      'Content-Type': 'application/json',
    },
    body: JSON.stringify({
      prompt: prompt,
      max_tokens: 100,
    }),
  });

  const gptData = await gptResponse.json();
  const robotCommand = gptData.choices[0].text.trim();

  // Send command to Arduino
  port.write(robotCommand + '\n', (err) => {
    if (err) {
      return console.log('Error on write:', err.message);
    }
    console.log('message written', robotCommand);
  });

  res.send({ message: 'Command sent to robot', command: robotCommand });
});

app.listen(3000, () => console.log('Server running on port 3000'));
