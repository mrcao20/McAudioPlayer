import QtAV 1.7

AVPlayer {
    enum PlayMode {
        Shuffle,
        Repeat,
        Single
    }
    property bool isPlaying: (playbackState === MediaPlayer.PlayingState)
    property int playMode: 0
}
