using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using HLSL.Elements.Base;
using HLSL.Values;
using rMind.Elements;

namespace HLSL.Elements
{
    public class MultipleNode : MathNodeBase
    {
        public MultipleNode(rMindBaseController parent) : base(parent)
        {

        }

        protected override string Result(HLSLResult a, HLSLResult b)
        {
            return string.Format("{0} * {1}", a.Value, b.Value);
        }
    }
}
