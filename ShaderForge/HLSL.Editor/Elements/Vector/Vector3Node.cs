using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HLSL.Elements
{
    using Base;
    using rMind.Elements;

    public class Vector3Node : RowContainerBase, IHLSLEditorNode
    {
        public Vector3Node(rMindBaseController parent) : base(parent)
        {

        }

        public string GetNodeValue(Node sender)
        {
            throw new NotImplementedException();
        }
    }
}
