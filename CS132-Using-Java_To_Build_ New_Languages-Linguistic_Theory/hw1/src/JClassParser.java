//Steven Salmons
//CS135- Frameworking New Languages on old

//Below is the JAVA token parser that a made-up language will break syntax down into
//Language sitting on this Java foundation will await response based on java interpretation of tokens

import java.util.*;
import java.io.IOException;

public class JClassParser {
    static String inputString;
    static int index = 0;
    static int errorflag = 0;
    private char token()
    { return(inputString.charAt(index)); }
    private void advancePtr()
    { if (index < (inputString.length()-1)) index++; }
    private void match(char T)
    { if (T == token()) advancePtr(); else error(); }
    private void error()
    {
        System.out.println("error at position: " + index);
        errorflag = 1;
        advancePtr();
    }
    //----------------------
    private void javaClass() {
        _classname();
        if(token() == 'X') {
            match('X');
            _classname();
        }
        match('B');
        _varlist();
        match(';');
        while(token() == 'P' || token() == 'V') {
            _method();
        }
        match('E');
    }

    private void _classname() {
        if(token() == 'C' || token() == 'D') {
            match(token());
        }
        else{
            error();
        }
    }

    private void _varlist() {
        _vardef();
        while(token() == 'I' || token() == 'S'){
            match(',');
            _vardef();
        }

    }

    private void _vardef() {
        if(token() == 'I' || token() == 'S') {
            _type();
            _varname();
        }
        else if(token() == 'C' || token() == 'D') {
            _classname();
            _varref();
        }
        else {
            error();
        }
    }

    private void _type() {
        if (token() == 'I' || token() == 'S'){
            match (token());
        }
        else{
            error();
        }
    }

    private void _varname() {

        _letter();

        while(  token() == 'Y' || token() == 'Z' ||
                token() == '0' || token() == '1' ||
                token() == '2' || token() == '3') {
            _char();
        }

    }

    private void _letter() {
        if (token() == 'Y' || token() == 'Z'){
            match (token());
        }
        else{
            error();
        }
    }

    private void _char() {
        if(token() == 'Y' || token() == 'Z') {
            _letter();
        }
        else if(token() == '0' || token() == '1' || token() == '2' || token() == '3') {
            _digit();
        }
        else {
            error();
        }
    }

    private void _digit() {
        if(token() == '0' || token() == '1' || token() == '2' || token() == '3') {
            match(token());
        }
        else {
            error();
        }
    }

    private void _integer() {
        _digit();
        while(token() == '0' || token() == '1' || token() == '2' || token() == '3') {
            _digit();
        }
    }

    private void _varref () {
        if (token() == 'J' || token() == 'K'){
            match (token());
        }
        else{
            error();
        }
    }

    private void _method() {
        _accessor();
        _type();
        _methodname();
        match('(');
        if(token() == 'I' || token() == 'S') {
            _varlist();
        }
        match(')');
        match('B');
        while(token() == 'F' || token() == 'Y'  || token() == 'Z'  || token() == 'W' ) {
            _statemt();
        }
        _returnstatemt();
        match('E');
    }

    private void _accessor() {
        if (token() == 'P' || token() == 'V'){
            match (token());
        }
        else{
            error();
        }
    }

    private void _methodname() {
        if (token() == 'M' || token() == 'N'){
            match (token());
        }
        else{
            error();
        }
    }

    private void _statemt() {

        if(token() == 'F') {
            _ifstatemt();
        }
        else if(token() == 'Y' || token() == 'Z') {
            _assignstatemt();
            match(';');
        }
        else if(token() == 'W') {
            _whilestatemt();

        }
        else {
            error();
        }

    }

    private void _ifstatemt() {
        match('F');
        _cond();
        match('T');
        match('B');
        while(token() == 'F' || token() == 'Y'  || token() == 'Z'  || token() == 'W' ) {
            _statemt();
        }
        match('E');
        if(token() == 'L') {
            match('L');
            match('B');
            while(token() == 'F' || token() == 'Y'  || token() == 'Z'  || token() == 'W' ) {
                _statemt();
            }
            match('E');
        }
    }

    private void _assignstatemt() {
        if(token() == 'Y' || token() == 'Z') {
            _varname();
            match('=');
            _mathexpr();
        }
        else if(token() == 'J' || token() == 'K') {
            _varref();
            match('=');
            _getvarref();
        }
        else {
            error();
        }
    }

    private void _mathexpr() {
        _factor();
        match('+');
        while(     token() == '0' || token() == '1' || token() == '2' ||
                token() == '3' || token() == 'Y' || token() == 'Z' ||
                token() == '(' || token() == 'J' || token() == 'K') {
            _factor();
        }
    }

    private void _factor() {
        _oprnd();
        match('*');
        while(token() == '0'  || token() == '1' || token() == '2' || token() == '3') {
            _oprnd();
        }
    }

    private void _oprnd() {
        if(token() == '0' || token() == '1' || token() == '2' || token() == '3') {
            _integer();
        }
        else if(token() == 'Y' || token() == 'Z') {
            _varname();
        }
        else if(token() == '(') {
            match('(');
            _mathexpr();
            match(')');
        }
        else if(token() == 'J' || token() == 'K') {
            _methodcall();
        }
        else {
            error();
        }

    }

    private void _getvarref() {
        if(token()=='O') {
            match('O');
            _classname();
            match('(');
            match(')');
        }
        else if(token() == 'J' || token() == 'K') {
            _methodcall();
        }
        else {
            error();
        }
    }

    private void _whilestatemt() {
        match('W');
        _cond();
        match('T');
        match('B');
        while(token()== 'F' || token() == 'Y' || token() == 'Z' || token() == 'W') {
            _statemt();
        }
        match('E');
    }

    private void _cond() {
        match('(');
        _oprnd();
        _operator();
        _oprnd();
        match(')');
    }

    private void _operator() {
        if(token() == '<') {
            match('<');
        }
        else if(token() == '=') {
            match('=');
        }
        else if(token() == '>') {
            match('>');
        }
        else if(token() == '!') {
            match('!');
        }
        else {
            error();
        }
    }

    private void _returnstatemt() {
        match('R');
        _varname();
        match(';');
    }

    private void _methodcall() {
        _varref();
        match('.');
        _methodname();
        match('(');
        if(token() == 'I' || token() == 'S') {
            _varlist();
        }
        match(')');

    }


    /* CODE BELOW PROVIDED BY INSTRUCTOR */
    private void start() {
        javaClass();
        match('$');
        if (errorflag == 0)
            System.out.println("legal." + "\n");
        else
            System.out.println("errors found." + "\n");
    }

    public static void main (String[] args) throws IOException {
        JClassParser rec = new JClassParser();
        Scanner input = new Scanner(System.in);
        System.out.print("\n" + "enter an expression: ");
        inputString = input.nextLine();
        rec.start();
    }

}