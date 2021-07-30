#include "callstack.h"

ostream &operator<<(ostream &out, Function_t &s)
{
  out << "Function " << s.name << " with " << s.numArguments << " args and ";
  out << s.numLocals << " locals";
  return out;
}

void CallStack::call(Function_t f, int RA, int BP, int *args, int *locals)
{
  /* TO DO! */

  for (int i = f.numArguments - 1; i >= 0; i--)
  {
    rawStack.push(args[i]);
  }
  rawStack.push(RA);
  rawStack.push(BP);
  for (int j = 0; j < f.numLocals; j++)
  {
    rawStack.push(locals[j]);
  }

  info.push(f);
}

Function_t CallStack::currentFunction(void)
{
  /* TO DO! */
  return info.peek();
}

int CallStack::getLocal(int n)
{

  Stack<int> Temp;

  int nLocal;
  Function_t i = info.peek();

  for (int j = 0; j < i.numLocals; j++)
  {
    Temp.push(rawStack.pop());
  }

  if (n <= i.numLocals)
  {
    for (int q = 0; q < n; q++)
    {
      rawStack.push(Temp.pop());
    }
  }

  nLocal = Temp.peek();

  for (int t = n + 1; t < i.numLocals; t++)
  {
    rawStack.push(Temp.pop());
  }

  //Temp.~Stack();
  return nLocal;
}

void CallStack::setLocal(int n, int val)
{
  /* TO DO! */
  Stack<int> Temp;

  int nLocal;
  Function_t i = info.peek();

  for (int j = 0; j < i.numLocals; j++)
  {
    Temp.push(rawStack.pop());
  }

  if (n <= i.numLocals)
  {
    for (int q = 0; q < n; q++)
    {
      rawStack.push(Temp.pop());
    }
  }

  Temp.pop();
  rawStack.push(val);

  for (int t = n + 1; t < i.numLocals; t++)
  {
    rawStack.push(Temp.pop());
  }

  //Temp.~Stack();
}

int CallStack::getArg(int n)
{
  /* TO DO! */
  Stack<int> Temp;
  int counter = 0;
  int nArg;
  Function_t i = info.peek();

  for (int j = 0; j < i.numLocals; j++)
  {
    Temp.push(rawStack.pop());
    counter++;
  }
  Temp.push(rawStack.pop()); // popping off BP
  counter++;
  Temp.push(rawStack.pop()); // popping off RA
  counter++;

  for (int k = 0; k < n; k++)
  {
    Temp.push(rawStack.pop());
    counter++;
  }

  nArg = rawStack.peek();

  for (int p = n; p < i.numArguments; p++)
  {
    Temp.push(rawStack.pop());
    counter++;
  }

  for (int m = 0; m < counter; m++)
  {
    rawStack.push(Temp.pop());
  }

  //Temp.~Stack();
  return nArg;
}

void CallStack::setArg(int n, int val)
{
  /* TO DO! */
  Stack<int> Temp;
  int counter = 0;
  int nArg;
  Function_t i = info.peek();

  for (int j = 0; j < i.numLocals; j++)
  {
    Temp.push(rawStack.pop());
    counter++;
  }
  Temp.push(rawStack.pop()); // popping off BP
  counter++;
  Temp.push(rawStack.pop()); // popping off RA
  counter++;

  for (int k = 0; k < n; k++)
  {
    Temp.push(rawStack.pop());
    counter++;
  }

  rawStack.pop();
  rawStack.push(val);

  for (int p = n; p < i.numArguments; p++)
  {
    Temp.push(rawStack.pop());
    counter++;
  }

  for (int m = 0; m < counter; m++)
  {
    rawStack.push(Temp.pop());
  }

  //Temp.~Stack();
}

int CallStack::getBP()
{
  /* TO DO! */
  Stack<int> Temp;

  int bp, counter = 0;
  Function_t i = info.peek();

  for (int j = 0; j < i.numLocals; j++)
  {
    Temp.push(rawStack.pop());
    counter++;
  }
  bp = rawStack.peek();

  for (int k = 0; k < counter; k++)
  {
    rawStack.push(Temp.pop());
  }
  //Temp.~Stack();

  return bp;
}

int CallStack::getRA()
{
  /* TO DO! */
  Stack<int> Temp;

  int ra, counter = 0;
  Function_t i = info.peek();

  for (int j = 0; j < i.numLocals; j++)
  {
    Temp.push(rawStack.pop());
    counter++;
  }
  Temp.push(rawStack.pop());
  counter++;
  ra = rawStack.peek();

  for (int k = 0; k < counter; k++)
  {
    rawStack.push(Temp.pop());
  }
  //Temp.~Stack();

  return ra;
}

void CallStack::do_return(void)
{

  /* TO DO! */

  Function_t i = info.peek();

  for (int j = 0; j < i.numLocals; j++)
    rawStack.pop();

  rawStack.pop(); // popping off BP
  rawStack.pop(); // popping off RA

  for (int r = 0; r < i.numArguments; r++)
  {
    rawStack.pop();
  }

  info.pop();
}

ostream &operator<<(ostream &out, CallStack &s)
{
  /* TO DO! */

  Function_t t = s.currentFunction();
  for (int i = t.numLocals - 1; i >= 0; i--)
  {
    out << s.getLocal(i) << " Local " << i << " for " << t.name << endl;
  }

  out << s.getBP() << " BP for " << t.name << endl;
  out << s.getRA() << " RA for " << t.name << endl;

  for (int k = 0; k < t.numArguments; k++)
  {
    out << s.getArg(k) << " Arg " << k << " for " << t.name;
  }

  return out;
}