#include "RadioPlayer.h"

RadioPlayer::RadioPlayer()
{
	inst = nullptr;
	player = nullptr;
}

RadioPlayer::~RadioPlayer()
{
	if (player)
		libvlc_media_player_release(player);

	if (inst)
		libvlc_release(inst);
}

bool RadioPlayer::init()
{
	const char *const args[] = { "--verbose=2" };

	inst = libvlc_new(1, args);

	if (!inst) {
		return false;
	}

	return true;
}

void RadioPlayer::play(const std::string &url)
{
	if (!inst)
		return;

	// 停止旧播放
	if (player) {
		libvlc_media_player_stop(player);
		libvlc_media_player_release(player);
		player = nullptr;
	}

	libvlc_media_t *media = libvlc_media_new_location(inst, url.c_str());
	player = libvlc_media_player_new_from_media(media);
	libvlc_media_release(media);

	libvlc_media_player_play(player);
	libvlc_audio_set_volume(player, 100);
}

void RadioPlayer::stop()
{
	if (player) {
		libvlc_media_player_stop(player);
	}
}