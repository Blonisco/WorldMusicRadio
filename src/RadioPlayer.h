#ifndef RadioPlayer_H_
#define RadioPlayer_H_

#include <string>
#include <vlc/vlc.h>

class RadioPlayer {
    private:
	libvlc_instance_t *inst;
	libvlc_media_player_t *player;

    public:
	RadioPlayer();
	~RadioPlayer();

	bool init();
	void play(const std::string &url);
	void stop();
};

#endif