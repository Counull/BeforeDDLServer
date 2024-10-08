// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: Authority.proto

#include "Authority.pb.h"
#include "Authority.grpc.pb.h"

#include <functional>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/impl/channel_interface.h>
#include <grpcpp/impl/client_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/sync_stream.h>
namespace Authority {

static const char* AccountService_method_names[] = {
  "/Authority.AccountService/Register",
  "/Authority.AccountService/Login",
  "/Authority.AccountService/SendSmsCode",
  "/Authority.AccountService/VerifySmsCode",
};

std::unique_ptr< AccountService::Stub> AccountService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< AccountService::Stub> stub(new AccountService::Stub(channel, options));
  return stub;
}

AccountService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_Register_(AccountService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Login_(AccountService_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_SendSmsCode_(AccountService_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_VerifySmsCode_(AccountService_method_names[3], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status AccountService::Stub::Register(::grpc::ClientContext* context, const ::Authority::RegisterRequest& request, ::Authority::RegisterResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::Authority::RegisterRequest, ::Authority::RegisterResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_Register_, context, request, response);
}

void AccountService::Stub::async::Register(::grpc::ClientContext* context, const ::Authority::RegisterRequest* request, ::Authority::RegisterResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::Authority::RegisterRequest, ::Authority::RegisterResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Register_, context, request, response, std::move(f));
}

void AccountService::Stub::async::Register(::grpc::ClientContext* context, const ::Authority::RegisterRequest* request, ::Authority::RegisterResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Register_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::Authority::RegisterResponse>* AccountService::Stub::PrepareAsyncRegisterRaw(::grpc::ClientContext* context, const ::Authority::RegisterRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::Authority::RegisterResponse, ::Authority::RegisterRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_Register_, context, request);
}

::grpc::ClientAsyncResponseReader< ::Authority::RegisterResponse>* AccountService::Stub::AsyncRegisterRaw(::grpc::ClientContext* context, const ::Authority::RegisterRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncRegisterRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status AccountService::Stub::Login(::grpc::ClientContext* context, const ::Authority::LoginRequest& request, ::Authority::LoginResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::Authority::LoginRequest, ::Authority::LoginResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_Login_, context, request, response);
}

void AccountService::Stub::async::Login(::grpc::ClientContext* context, const ::Authority::LoginRequest* request, ::Authority::LoginResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::Authority::LoginRequest, ::Authority::LoginResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Login_, context, request, response, std::move(f));
}

void AccountService::Stub::async::Login(::grpc::ClientContext* context, const ::Authority::LoginRequest* request, ::Authority::LoginResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Login_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::Authority::LoginResponse>* AccountService::Stub::PrepareAsyncLoginRaw(::grpc::ClientContext* context, const ::Authority::LoginRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::Authority::LoginResponse, ::Authority::LoginRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_Login_, context, request);
}

::grpc::ClientAsyncResponseReader< ::Authority::LoginResponse>* AccountService::Stub::AsyncLoginRaw(::grpc::ClientContext* context, const ::Authority::LoginRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncLoginRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status AccountService::Stub::SendSmsCode(::grpc::ClientContext* context, const ::Authority::SendSmsCodeRequest& request, ::Authority::SendSmsCodeResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::Authority::SendSmsCodeRequest, ::Authority::SendSmsCodeResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_SendSmsCode_, context, request, response);
}

void AccountService::Stub::async::SendSmsCode(::grpc::ClientContext* context, const ::Authority::SendSmsCodeRequest* request, ::Authority::SendSmsCodeResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::Authority::SendSmsCodeRequest, ::Authority::SendSmsCodeResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SendSmsCode_, context, request, response, std::move(f));
}

void AccountService::Stub::async::SendSmsCode(::grpc::ClientContext* context, const ::Authority::SendSmsCodeRequest* request, ::Authority::SendSmsCodeResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SendSmsCode_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::Authority::SendSmsCodeResponse>* AccountService::Stub::PrepareAsyncSendSmsCodeRaw(::grpc::ClientContext* context, const ::Authority::SendSmsCodeRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::Authority::SendSmsCodeResponse, ::Authority::SendSmsCodeRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_SendSmsCode_, context, request);
}

::grpc::ClientAsyncResponseReader< ::Authority::SendSmsCodeResponse>* AccountService::Stub::AsyncSendSmsCodeRaw(::grpc::ClientContext* context, const ::Authority::SendSmsCodeRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncSendSmsCodeRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status AccountService::Stub::VerifySmsCode(::grpc::ClientContext* context, const ::Authority::VerifySmsCodeRequest& request, ::Authority::VerifySmsCodeResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::Authority::VerifySmsCodeRequest, ::Authority::VerifySmsCodeResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_VerifySmsCode_, context, request, response);
}

void AccountService::Stub::async::VerifySmsCode(::grpc::ClientContext* context, const ::Authority::VerifySmsCodeRequest* request, ::Authority::VerifySmsCodeResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::Authority::VerifySmsCodeRequest, ::Authority::VerifySmsCodeResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_VerifySmsCode_, context, request, response, std::move(f));
}

void AccountService::Stub::async::VerifySmsCode(::grpc::ClientContext* context, const ::Authority::VerifySmsCodeRequest* request, ::Authority::VerifySmsCodeResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_VerifySmsCode_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::Authority::VerifySmsCodeResponse>* AccountService::Stub::PrepareAsyncVerifySmsCodeRaw(::grpc::ClientContext* context, const ::Authority::VerifySmsCodeRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::Authority::VerifySmsCodeResponse, ::Authority::VerifySmsCodeRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_VerifySmsCode_, context, request);
}

::grpc::ClientAsyncResponseReader< ::Authority::VerifySmsCodeResponse>* AccountService::Stub::AsyncVerifySmsCodeRaw(::grpc::ClientContext* context, const ::Authority::VerifySmsCodeRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncVerifySmsCodeRaw(context, request, cq);
  result->StartCall();
  return result;
}

AccountService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      AccountService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< AccountService::Service, ::Authority::RegisterRequest, ::Authority::RegisterResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](AccountService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::Authority::RegisterRequest* req,
             ::Authority::RegisterResponse* resp) {
               return service->Register(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      AccountService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< AccountService::Service, ::Authority::LoginRequest, ::Authority::LoginResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](AccountService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::Authority::LoginRequest* req,
             ::Authority::LoginResponse* resp) {
               return service->Login(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      AccountService_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< AccountService::Service, ::Authority::SendSmsCodeRequest, ::Authority::SendSmsCodeResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](AccountService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::Authority::SendSmsCodeRequest* req,
             ::Authority::SendSmsCodeResponse* resp) {
               return service->SendSmsCode(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      AccountService_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< AccountService::Service, ::Authority::VerifySmsCodeRequest, ::Authority::VerifySmsCodeResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](AccountService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::Authority::VerifySmsCodeRequest* req,
             ::Authority::VerifySmsCodeResponse* resp) {
               return service->VerifySmsCode(ctx, req, resp);
             }, this)));
}

AccountService::Service::~Service() {
}

::grpc::Status AccountService::Service::Register(::grpc::ServerContext* context, const ::Authority::RegisterRequest* request, ::Authority::RegisterResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status AccountService::Service::Login(::grpc::ServerContext* context, const ::Authority::LoginRequest* request, ::Authority::LoginResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status AccountService::Service::SendSmsCode(::grpc::ServerContext* context, const ::Authority::SendSmsCodeRequest* request, ::Authority::SendSmsCodeResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status AccountService::Service::VerifySmsCode(::grpc::ServerContext* context, const ::Authority::VerifySmsCodeRequest* request, ::Authority::VerifySmsCodeResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace Authority

