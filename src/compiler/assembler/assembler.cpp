#include "assembler.h"

namespace comp {
    Assembler::Assembler(const InstructionSet& instuctions)
            : instuctions(instuctions) {

    }

    vector<Token> Assembler::register_labels(vector<Token> tokens) {
        word instructions = 0;

        for(auto it = tokens.begin(); it != tokens.end();) {
            auto token = *it;
            const auto tokenType = token.get_type();

            if(tokenType == WORD) {
                auto instruction = instuctions.find(to_upper_case(token.get_value()));

                if(!instruction.is_24bit_instruction())
                    ++it;

                ++instructions;

                if(it == tokens.end())
                    break;
            } else if(tokenType == LABEL_START) {
                it = tokens.erase(it);

                string label = token.get_value();

                // We save label without last ':' symbol
                if(label[label.size() - 1] == ':')
                    label.pop_back();

                if(labels.contains(label))
                    throw runtime_error("Label " + label + " is already defined");

                labels.insert({label, instructions});

                if(it == tokens.end())
                    break;
            }

            ++it;
        }

        return tokens;
    }

    word Assembler::get_label_value(string label) const {
        if(!labels.contains(label))
            throw runtime_error("Not defined label " + label);

        return labels.at(label);
    }

    InstructionList Assembler::tokenize(vector<Token> tokens) {
        InstructionList list;

        tokens = register_labels(tokens);

        for(auto it = tokens.begin(); it != tokens.end();) {
            auto token = *it;
            const auto tokenType = token.get_type();

            if(tokenType == WORD) {
                auto instruction = instuctions.find(to_upper_case(token.get_value()));

                if(!instruction.is_24bit_instruction() && !instruction.is_halt()) {
                    ++it;

                    if(it == tokens.end())
                        throw std::runtime_error("Expected keyword argument after " + token.get_value() + " keyword");

                    auto argumentToken = *it;
                    auto argumentType = argumentToken.get_type();

                    if(argumentType == NUMERIC)
                        instruction.argument.val = parse_16bit_numeric(argumentToken.get_value());
                    else if(argumentType == LABEL)
                        instruction.argument.val = get_label_value(argumentToken.get_value());
                    else if(argumentType == LABEL_START)
                        throw runtime_error("Unexpected label definition, after" + token.get_value() + " keyword");
                    else
                        throw runtime_error("Expected numeric token, after " + token.get_value() + " keyword");
                }

                list.add(instruction);
            } else if(tokenType == LABEL) {
                throw runtime_error("Unexpected label usage");
            } else if(tokenType == LABEL_START) {
                throw runtime_error("Unexpected label definition");
            } else if(tokenType == NUMERIC) {
                throw runtime_error("Unexpected numeric value");
            };

            ++it;
        }

        return list;
    }

    void Assembler::clear_labels() {
        labels.clear();
    }
}