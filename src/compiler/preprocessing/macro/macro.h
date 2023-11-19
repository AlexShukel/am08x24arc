#pragma once

#include <string>
#include <vector>
#include <regex>
#include <string>
#include <functional>

using namespace std;

namespace comp {
    struct Preprocessor;

    class Macro {
        protected:
            string label;
            string body;

            vector<string> argsLabels;

        public:
            virtual bool comp_time_process(Preprocessor&, vector<string>&) { return true; }
            virtual bool pre_comp_time_process(Preprocessor&, vector<string>&) { return true; }

            Macro(const string& label, const string& body);
            Macro(const string& label, const string& body, const vector<string>& argsLabels);

            const string& get_label() const;
            const string& get_body() const;
            const vector<string>& get_arg_labels() const;
            size_t get_arg_count() const;

            bool is_zero_arg_macro() const;

            string paste_args(const vector<string>& args) const;
    };
}