# 🎵 Convert to Sound in C++

A simple C++ program that converts user-input text into speech using the `espeak` tool. This mini-project was created as a practice for working with system commands and sound processing.

## 🚀 How It Works

The program:
1. Prompts the user to enter a sentence.
2. Uses `espeak` to generate a `.wav` audio file from the text.
3. Plays the generated sound file using `aplay` or any available system player.

## 📁 Project Structure


## ⚙️ Getting Started

### 1. Install Dependencies

On Linux:
`bash`
sudo apt install espeak
sudo apt install alsa-utils  # for 'aplay'

### 2. Compile the Program

g++ pretvoriVZvok.cpp -o text_to_speech

### 3. Run the Program

./text_to_speech
