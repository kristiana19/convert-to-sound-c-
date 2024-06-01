#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>

// Vključite knjižnico za pretvorbo besedila v govor
#include <cstdlib>

// Vključite knjižnico za predvajanje zvoka
#include <SDL2/SDL.h>

using namespace std;

// Funkcija za pretvorbo besedila v govor in predvajanje zvoka
void pretvoriVZvok(const string& besedilo) {
    //Pretvorba besedila v govor
    //system(("espeak-ng -ven-us -s 150 -g 10 -p 50 -z \"" + besedilo + "\" --stdout > zvok.wav").c_str());

    //Sestavi ukaz, ki bo izvedel pretvorbo besedila v govor z uporabo espeak-ng
    string ukaz = "espeak-ng -ven-us -s 150 -g 10 -p 50 -z \"" + besedilo + "\"";
    //izvedi ukaz z uporabo system
    system(ukaz.c_str());

    // Predvajanje zvoka (inicializacija knjižnice SDL za predvajanje avdio vsebine)
    SDL_Init(SDL_INIT_AUDIO);
    //definicija spremenljivk za zvocne podatke
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8* wavBuffer;

    //Naloži zvočno datoteko z imenom "zvok.wav" in preveri, 
    //ali je bilo naloženje uspešno
    if(SDL_LoadWAV("zvok.wav", &wavSpec, &wavBuffer, &wavLength) == nullptr) {
        cerr << "Napaka pri nalaganju zvoka: " << SDL_GetError() << endl;
        return;
    }

    //Odpre avdio napravo za predvajanje zvoka
    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(nullptr, 0, &wavSpec, nullptr, 0);
    if(deviceId == 0) {
        cerr << "Napaka pri odpiranju avdio naprave: " << SDL_GetError() << endl;
        SDL_FreeWAV(wavBuffer);
        return;
    }

    //Doda zvočni buffer v predvajalno vrsto in zažene predvajanje zvoka
    SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);

    //Počaka, da se zvok predvaja
    SDL_Delay(wavSpec.samples * 1000 / wavSpec.freq);

    //Zapre avdio napravo, sprosti zvočni buffer in izhod iz knjižnice SDL
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
    SDL_Quit();
}

int main() {
    string besedilo;
    cout << "Vnesite besedilo, ki naj se pretvori v zvok: ";
    getline(cin, besedilo);

    pretvoriVZvok(besedilo);

    return 0;
}
