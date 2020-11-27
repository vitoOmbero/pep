import subprocess as sb
import os

cwd = os.getcwd()

os.environ['LD_LIBRARY_PATH'] = cwd

# TODO : built type as argument

tests_dir = "../install/bin/Tests/Debug"

projects = [
('hello-bin', './'),
('app.out', './'),
('test.so', './subdir/'),
('test_with_epoit.so', './')
]

results = list()

def fail_test(tag:str):
    results.append((tag, "==FAILED=="))
    return

def pass_test(tag:str):
    results.append((tag, "+"))
    return

def chdir(path: str) -> str:
    if path == './':
        return os.path.join(cwd, tests_dir)
    return os.path.join(cwd, tests_dir + path)


for p_name, p_path in projects:
    dir = chdir(p_path)
    print("test is executable in ", dir)
    if os.path.exists(dir) == False:
        print("Could not find target dir ", p_path)
        fail_test(p_name)
    if os.path.exists(dir+p_name) == False:
        print("Could not find target executable ", p_name)
        fail_test(p_name)
    else:
        print(">> run: ", p_name, " in dir: ", dir)       
        code = sb.check_call([dir+p_name+' test\n'], shell=True)
        print( "  return code << ", code);
        pass_test(p_name)
        
        # notes how to run 
        
        #proc = sb.Popen(['./'+dir+p_name], shell=True, stdin=sb.PIPE, stdout=sb.PIPE, stderr=sb.PIPE)
        #out, err = proc.communicate('test\n')
        #print("ReturnCode: ", proc.returncode)
        #assert proc.returncode == 0

        # out, err = proc.communicate('hello\n')
        # assert out == 'hello\n'
        # assert err == ''

        # result = sb.run([dir + p_name], stdout=sb.PIPE, cwd=cwd)
        # if result.returncode != 0:
             #print("error: \nargs: ", result.args, "\nstdout: ", result.stdout, "\nreturncode: {}", result.returncode)
             #break
        

for rec in results:
    print(rec)


