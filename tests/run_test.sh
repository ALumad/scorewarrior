#/bin/bash
ls scripts | xargs -I {} python3 test.py ../build/bin/scorewarrior scripts/{} answer/{}
