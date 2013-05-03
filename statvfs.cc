#include <node.h>
#include <v8.h>

#include <sys/statvfs.h>

using namespace v8;



Handle<Value> Statvfs(const Arguments& args) {
    HandleScope scope;
    if (args.Length() < 1 || !args[0]->IsString()) {
        ThrowException(Exception::TypeError(String::New("No path given")));
        return scope.Close(Undefined());
    }

    Local<String> path = args[0]->ToString();
    String::AsciiValue  ascii(path);

    char *pathStr = *ascii;
    printf("%s\n", pathStr);

    struct statvfs vfs;
    int res = statvfs(pathStr, &vfs);

    if (res != 0) {
        ThrowException(Exception::TypeError(String::New("statvfs call failed")));
    }
    
    Local<Object> obj = Object::New();
    long unsigned int free_space = vfs.f_bfree * vfs.f_bsize; 
    long unsigned int total_space = vfs.f_blocks * vfs.f_frsize;
    long unsigned int used_space = free_space - total_space;

    obj->Set(String::NewSymbol("f_bsize"), Number::New(vfs.f_bsize));
    obj->Set(String::NewSymbol("f_frsize"), Number::New(vfs.f_frsize));
    obj->Set(String::NewSymbol("f_blocks"), Number::New(vfs.f_blocks));
    obj->Set(String::NewSymbol("f_bfree"), Number::New(vfs.f_bfree));
    obj->Set(String::NewSymbol("f_bavail"), Number::New(vfs.f_bavail));
    obj->Set(String::NewSymbol("f_files"), Number::New(vfs.f_files));
    obj->Set(String::NewSymbol("f_ffree"), Number::New(vfs.f_ffree));
    obj->Set(String::NewSymbol("f_favail"), Number::New(vfs.f_favail));
    obj->Set(String::NewSymbol("f_fsid"), Number::New(vfs.f_fsid));
    obj->Set(String::NewSymbol("f_flag"), Number::New(vfs.f_flag));
    obj->Set(String::NewSymbol("f_namemax"), Number::New(vfs.f_namemax));

    obj->Set(String::NewSymbol("free_space"), Number::New(free_space));
    obj->Set(String::NewSymbol("total_space"), Number::New(total_space));
    obj->Set(String::NewSymbol("used_space"), Number::New(used_space));
    
    return scope.Close(obj);
}

// Statvfs factory
Handle<Value> StatvfsFactory(const Arguments& args) {
    HandleScope scope;
    Local<FunctionTemplate> tpl = FunctionTemplate::New(Statvfs);
    Local<Function> func = tpl->GetFunction();
    func->SetName(String::NewSymbol("st"));

    return scope.Close(func);
}

void init(Handle<Object> exports, Handle<Object> module) {
    module->Set(String::NewSymbol("exports"),
        FunctionTemplate::New(Statvfs)->GetFunction());
}

NODE_MODULE(statvfs, init)