#ifndef MEMFUN_ADAPTER_H
#define MEMFUN_ADAPTER_H
template <typename RetType, typename ClassType, typename ArgType>
class MFA_1arg {
		
    RetType (ClassType::*pointer) (ArgType);
	public:
		MFA_1arg( RetType (ClassType::*_pointer) (ArgType) ) : pointer(_pointer) {}
		RetType operator() ( ClassType &element, ArgType data ) const {
			return (element.*pointer) (data); //call
		}
};

//helper functions
//for non-const member function
template <typename RetType, typename ClassType, typename ArgType>
MFA_1arg<RetType,ClassType,ArgType> mfp_1arg(RetType (ClassType::*pointer) (ArgType) ) { 
	return MFA_1arg<RetType, ClassType, ArgType>(pointer); 
}
#endif
