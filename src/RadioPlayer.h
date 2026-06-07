#ifndef RadioPlayer_H_
#define RadioPlayer_H_

#include <string>
#include <vlc/vlc.h>

class RadioPlayer {
    private:
	libvlc_instance_t *inst;
	libvlc_media_player_t *player;
	bool is_playing_ = false;
	bool is_muted_ = false;

    public:
	RadioPlayer();
	~RadioPlayer();

	void resume();
	bool is_playing();
	bool is_muted();
	bool init();
	void play(const std::string &url);
	void stop();
	void change_muted();
};

#endif
