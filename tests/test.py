import sys
import subprocess

sw = sys.argv[1]
path_scenario = sys.argv[2]
path_answer = sys.argv[3]

result = subprocess.run([sw, path_scenario], stdout=subprocess.PIPE)
result = result.stdout.decode("ascii").splitlines()

with open(path_answer) as f:
    answer = f.read().splitlines()

for i in range(0,len(answer)):
    if (answer[i] != result[i]):
        print(f'result: {result[i]} \ncorrect {answer[i]}')
        assert(answer[i] == result[i])

print("SUCCESS",path_scenario)