//
// Created by mw on 31.07.2020.
//

#ifndef IOTCOMMONS_COLLECTRESULT_H
#define IOTCOMMONS_COLLECTRESULT_H

template<class value_type>
struct CollectResult {
  enum ErrorCode {
    SUCCESS,
    OTHER_ERROR
  };

  ErrorCode error_code;
  value_type value;
};

#endif //IOTCOMMONS_COLLECTRESULT_H
