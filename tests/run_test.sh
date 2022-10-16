#/bin/bash
ls scripts | xargs -I {} python3 test.py ../build/scorewarrior scripts/{} answer/{}