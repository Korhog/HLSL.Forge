namespace HLSL.Elements.Base
{
    using rMind.Elements;
    using rMind.Nodes;

    /// <summary>
    /// Форматы нодов
    /// </summary>
    public enum NodeValueFormat
    {
        NONE,
        FLOAT,
        FLOAT2,
        FLOAT3,
        FLOAT4,
    }

    /// <summary>
    /// Node для Shader Forge
    /// </summary>
    public class Node : rMindBaseNode
    {
        public NodeValueFormat NodeValueFormat { get; set; } = NodeValueFormat.NONE;

        public Node(rMindBaseElement parent) : base(parent)
        {

        }

        protected override bool ValidateAttach(rMindBaseWireDot dot)
        {
            if (!base.ValidateAttach(dot))
                return false;
            if (dot.ReverseDot.Node != null && dot.ReverseDot.Node is Node)
            {
                Node node = dot.ReverseDot.Node as Node;
                if (node.NodeValueFormat != NodeValueFormat) return false;
            }

            return true;
        }

        public virtual string GetValue()
        {
            return (Parent as IHLSLEditorNode)?.GetNodeValue(this);
        }
    }
}
