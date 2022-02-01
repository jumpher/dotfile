#!/usr/bin/env python3

import os
import argparse
import stagger


def notify(song, album, artist, icon='music'):
    command = f'''
    notify-send -i "{icon}" "🎵 {song}" "<i>📀 {album}</i>\n<b>👄 {artist}</b>"
'''
    os.system(command)


def get_cover(mp3):
    if (mp3.picture):
        data = mp3[stagger.id3.APIC][0].data
        icon = '/tmp/xyz.jpg'
        with open(icon, "wb") as outfile:
            outfile.write(data)
    else:
        icon = 'music'
    return icon


def main(filename):
    mp3 = stagger.read_tag(filename)
    icon = get_cover(mp3)
    notify(mp3.title, mp3.album, mp3.artist, icon)


def check_file(filename):
    try:
        f = open(filename)
        # Do something with the file
    except IOError:
        print("File not accessible")
        return False
    finally:
        f.close()

    return True


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("filename")
    args = parser.parse_args()

    if check_file(args.filename):
        main(args.filename)
