import McMultimedia 1.0

MediaPlayer {
    enum PlayMode {
        Shuffle,
        Repeat,
        Single
    }
    property bool isPlaying: (state === MediaPlayer.PlayingState)
    property int playMode: 0
}
