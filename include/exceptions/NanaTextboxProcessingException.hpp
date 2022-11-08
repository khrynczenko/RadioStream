#ifndef NANATEXTBOXPROCESSINGEXCEPTION_HPP
#define NANATEXTBOXPROCESSINGEXCEPTION_HPP

#include <exception>
#include <string>
class NanaTextboxProcessingException : public std::exception {
   public:
    [[nodiscard]] char const* what() const noexcept override;
};

#endif