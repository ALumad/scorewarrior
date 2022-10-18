#/bin/bash
ls scripts | xargs -I {} python3 test.py ../build/src/bin/scorewarrior scripts/{} answer/{}
