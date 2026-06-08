#version 460 core

out vec4 FragColor;

const float infinity = 1e30f;
const float epsilon = 1.192092896e-07f;

in vec2 screen;

struct Point
{
    float t, u ,v;
};

uniform vec3 camPos;

uniform vec3 camRight;
uniform vec3 camUp;
uniform vec3 camForward;

uniform float width;
uniform float height;

Point RayHitTri(vec3 v0, vec3 v1, vec3 v2, vec3 O, vec3 D);

struct Vertex
{
    vec3 pos;
    vec2 texCoords;
    vec3 normal;
    vec3 color;

    vec3 lightning;
};

layout(std430, binding = 0) readonly buffer VertexBuffer
{
    Vertex worldVertices[];
};

uniform sampler2D worldTex[1000];

void main()
{
    Point point;

    float fov = tan(radians(45.0f) / 2.0f);
    float aspect = width / height;

    vec3 camDir = normalize(camForward + screen.x * aspect * fov * camRight + screen.y * fov * camUp);

    vec3 lightPos = normalize(vec3(2.0f, 2.0f, 0.0f));

    FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);

    vec3 color = vec3(0.0f, 0.0f, 0.0f);
    float t_min = infinity;
    for (int i = 0; i < worldVertices.length(); i+=3)
    {
        vec3 v0 = worldVertices[i].pos;
        vec3 v1 = worldVertices[i+1].pos;
        vec3 v2 = worldVertices[i+2].pos;

        point = RayHitTri(v0, v1, v2, camPos, camDir);

        if (point.t > 0.0f && point.t < t_min)
        {
            /*
            color = worldVertices[i].color * (1.0f - point.u - point.v) + 
                    worldVertices[i+1].color * point.u + 
                    worldVertices[i+2].color * point.v;
            */

            vec2 texCoords = worldVertices[i].texCoords * (1.0f - point.u - point.v) + 
                             worldVertices[i+1].texCoords * point.u + 
                             worldVertices[i+2].texCoords * point.v;

            if (i > 71)
            {
                color = worldVertices[i].color * (1.0f - point.u - point.v) + 
                        worldVertices[i+1].color * point.u + 
                        worldVertices[i+2].color * point.v;
            }
            else{
                color = texture(worldTex[0], texCoords).rgb;
            }
            
            if (worldVertices[i].lightning.x > 0.0f)
            {
                vec3 normal = worldVertices[i].normal * (1.0f - point.u - point.v) + 
                          worldVertices[i+1].normal * point.u + 
                          worldVertices[i+2].normal * point.v;   

                vec3 ambient = 0.1f * color;
                vec3 lightDir = normalize(lightPos - (camPos + camDir * point.t));
                vec3 diffuse = max(dot(normal, lightDir), 0.0f) * color;
                vec3 spec = vec3(0.0f) * color;

                 for (int i = 0; i < worldVertices.length(); i+=3)
                 {
                        vec3 v0 = worldVertices[i].pos;
                        vec3 v1 = worldVertices[i+1].pos;
                        vec3 v2 = worldVertices[i+2].pos;
    
                        Point shadowPoint = RayHitTri(v0, v1, v2, camPos + camDir * point.t, lightDir);
    
                        if (shadowPoint.t > 0.0f && shadowPoint.t < length(lightPos - (camPos + camDir * point.t)))
                        {
                            //diffuse *= 0.2f;
                            spec = pow(max(dot(reflect(-lightDir, normal), -camDir), 0.0f), 32.0f) * texture(worldTex[0], texCoords).rgb;
                            break;
                        }
                 }
                          
                FragColor = vec4(ambient + diffuse + spec, 1.0f);
            }
            else
            {
                FragColor = vec4(worldVertices[i].color, 1.0f);
            }

            t_min = point.t;
        }
    }
    
}

Point RayHitTri(vec3 v0, vec3 v1, vec3 v2, vec3 O, vec3 D)
{
    Point point;

    vec3 e1 = v0 - v1;
    vec3 e2 = v0 - v2;
    vec3 s = v0 - O;

    float det = dot(D, cross(e1, e2));
    if (abs(det) < epsilon)
    {
        point.t = -1.0f; point.u = -1.0f; point.v = -1.0f;
        return point;
    }

    float invDet = 1.0f / det;

    float t = dot(s, cross(e1, e2)) * invDet;
    float u = dot(s, cross(e2, D)) * invDet;
    float v = dot(s, cross(D, e1)) * invDet;

    if (t >= 0.0f && u >= 0.0f && v >= 0.0f && u + v <= 1.0f)
    {
        point.t = t; point.u = u; point.v = v;
        return point;
    }
    else
    {
        point.t = -1.0f; point.u = -1.0f; point.v = -1.0f;
        return point;
    }
}