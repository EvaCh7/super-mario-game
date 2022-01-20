#pragma once


#include<string>

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


class Audio {

private:

	ALLEGRO_SAMPLE* sample;
	ALLEGRO_SAMPLE_ID* sampleID;
public:
	void playSample(std::string);
	void stopSample();
	//Audio();


};

/*
Audio::Audio() {
	this->sample = NULL;
	this->sampleID = NULL;
}*/

void Audio::playSample(std::string path) {
	al_reserve_samples(1);
	//"config/sound.mp3"
	this->sample = al_load_sample(path.c_str());
	al_play_sample(sample, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, this->sampleID);

}

void Audio::stopSample() {
	if(this->sampleID)
	al_stop_sample(this->sampleID);
}