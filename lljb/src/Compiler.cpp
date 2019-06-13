#include "lljb/Compiler.hpp"
#include "lljb/MethodBuilder.hpp"

namespace lljb{

Compiler::Compiler(Module * module)
    : _typeDictionary(),
      _module(module){}

void Compiler::compile(){
    for (auto func = _module->getLLVMModule()->getFunctionList().begin();
    func != _module->getLLVMModule()->getFunctionList().end() ; func++){
        _compiledFunctions.push_back(compileMethod(*func));
    }
}

JittedFunction Compiler::compileMethod(llvm::Function &func){
    MethodBuilder methodBuilder(&_typeDictionary, func);
    void * result = 0;
    methodBuilder.Compile(&result);
    return (JittedFunction) result;
}


} /** namespace lljb */
